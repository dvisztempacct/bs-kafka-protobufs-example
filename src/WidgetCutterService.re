module K = Kafka_raw;
module BlankWidget = Grpc.Assemblyline.BlankWidget;
module CutWidget = Grpc.Assemblyline.CutWidget;
let blankWidgetTopic = "blank-widget";
let cutWidgetTopic = "cut-widget";
let zookeeperAddress = Util.getEnvExn("ZOOKEEPER");
let clientIdentifier = "WidgetCutterService.re";

let client = K.Client.make(zookeeperAddress, clientIdentifier);

module Consumer = {
  let onError = Js.log2("error=");

  let onOffsetOutOfRange = e =>
    failwith("offsetOutOfRange=" ++ Js.String.make(e));

  let make = producer => {
    /* Our glorious message handler a la consumer */
    let onMessage = receipt => {
      /* Obtain buffer */
      let buffer = receipt |. K.Consumer.bufferValue;

      /* Decode buffer */
      let blankWidget = buffer |. BlankWidget.decode;

      /* Roll some logs */
      blankWidget |. Util.blankWidgetToString |> Js.log2("rx:");

      /* Access message fields */
      let widgetCondition =
        blankWidget |. BlankWidget.conditionGet |. Belt.Option.getExn;

      /* Some logs */
      Js.log("cutting widget...");

      /* Do an async API call (cut the widget) */
      widgetCondition
      |> Mock.cutWidget((widgetCondition, numTeeth) => {
           /* Construct a message */
           let cutWidget =
             CutWidget.make(~condition=widgetCondition, ~numTeeth, ());

           /* Roll some logs */
           Js.log("widget cut!");
           cutWidget |. Util.cutWidgetToString |> Js.log2("tx:");

           /* Encode message to buffer */
           cutWidget
           |> CutWidget.encode
           /* Send message a la producer */
           |> GenericProducer.send(cutWidgetTopic, producer)
           |> ignore
         });
    };

    let consumer =
      K.Consumer.make3(
        client,
        [|K.Consumer.Payload.t(~topic=blankWidgetTopic, ())|],
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
