module K = Kafka_raw;
module CutWidget = Grpc.Assemblyline.CutWidget;
module PaintedWidget = Grpc.Assemblyline.PaintedWidget;
let cutWidgetTopic = "cut-widget";
let paintedWidgetTopic = "painted-widget";
let zookeeperAddress = Util.getEnvExn("ZOOKEEPER");
let clientIdentifier = "WidgetPainterService.re";

let client = K.Client.make(zookeeperAddress, clientIdentifier);

module Consumer = {
  let onError = Js.log2("error=");

  let onOffsetOutOfRange = e =>
    failwith("offsetOutOfRange=" ++ Js.String.make(e));

  let make = producer => {
    let onMessage = receipt => {
      let buffer = receipt |. K.Consumer.bufferValue;
      let cutWidget = buffer |. CutWidget.decode;
      cutWidget |. Util.cutWidgetToString |> Js.log2("rx:");
      let condition = cutWidget |. CutWidget.conditionGet |. Belt.Option.getExn;
      let numTeeth = cutWidget |. CutWidget.numTeethGet |. Belt.Option.getExn;

      Js.log("painting widget...");
      condition
      |> Mock.paintWidget((condition, paintJob) => {
           let paintedWidget =
             PaintedWidget.make(~condition, ~numTeeth, ~paintJob, ());

           Js.log("widget painted!");
           paintedWidget |. Util.paintedWidgetToString |> Js.log2("tx:");

           paintedWidget
           |> PaintedWidget.encode
           |> GenericProducer.send(paintedWidgetTopic, producer)
           |> ignore;
         });
    };

    let consumer =
      K.Consumer.make3(
        client,
        [|K.Consumer.Payload.t(~topic=cutWidgetTopic, ())|],
        K.Consumer.MakeOptions.t(~encoding="buffer", ()),
      );

    consumer |. K.Consumer.on(`error(onError));

    consumer |. K.Consumer.on(`offsetOutOfRange(onOffsetOutOfRange));

    consumer |. K.Consumer.on(`message(onMessage));

    consumer;
  };
};

let producer =
  client
  |. GenericProducer.make(producer => {
       let consumer = producer |> Consumer.make;
       ();
     });
