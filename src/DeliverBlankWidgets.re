module K = Kafka_raw;
module WidgetCondition = Grpc.Assemblyline.WidgetCondition;
module BlankWidget = Grpc.Assemblyline.BlankWidget;

/* Initialize our RNG */
let rng = Js.Date.now() |. int_of_float |. Random.init;

/* Topic we want to publish to */
let blankWidgetTopic = "blank-widget";

/* Our Zookeeper address */
let zookeeperAddress = Util.getEnvExn("ZOOKEEPER");

/* How we identify ourselves */
let clientIdentifier = "DeliverBlankWidgets.re";

/* Roll some logs */
Js.log3(clientIdentifier, "connecting to zookeeper at ", zookeeperAddress);

/* Instantiate Zookeeper/Kafka connection */
let client = K.Client.make(zookeeperAddress, clientIdentifier);

/* Instantiate Producer */
client
|. GenericProducer.make(producer => {
     /* Construct a message */
     let blankWidget =
       BlankWidget.make(
         ~condition=
           WidgetCondition.(
             Random.float(1.0) < 0.9 ?
               WidgetConditionAdequate : WidgetConditionDefective
           ),
         (),
       );

     /* Roll some logs */
     blankWidget |. Util.blankWidgetToString |> Js.log2("rx:");

     /* Encode our message to a buffer */
     blankWidget
     |> BlankWidget.encode
     /* Send the message a la Producer */
     |> GenericProducer.send(blankWidgetTopic, producer)
     |. Future.get(_ => {
          Js.log("successfully delivered blank widget!");
          client |. K.Client.close(() => Js.log("client closed! bye!"));
        });
   });
