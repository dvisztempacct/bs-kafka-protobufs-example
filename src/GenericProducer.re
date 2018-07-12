module K = Kafka_raw;

/* A generic error handler */
let errorHandler = error => {
  Js.log2("error: ", error);
  failwith("Fatal");
};

let make = (client, readyHandler) => {
  /* Instantiate a producer */
  let producer = K.Producer.make(client);
  /* Register error handler */
  producer |. K.Producer.on(`error(errorHandler));
  /* Register 'ready' event handler */
  producer |. K.Producer.on(`ready(() => producer |. readyHandler));
  ();
};

/* A simplified interface to send messages */
let send = (topic, producer, message: Node.buffer) => Future.make(resolve => {
  let messages = [|message|];
  producer
  |. K.Producer.send(
       [|K.Producer.ProduceRequest.t(~topic, ~messages, ())|], (err, res) =>
       if (err |. Js.Nullable.test) {
         Js.log2("message send success:", res);
         resolve(res |. Belt.Result.Ok)
       } else {
         err |> Js.String.make |> errorHandler;
       }
     );
});
