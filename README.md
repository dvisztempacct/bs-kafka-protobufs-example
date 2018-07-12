# bs-kafka example

We're in the business of making widgets, and this is our microservices solution!

To use, first clone this repo, then:

```
# Export something like this:
export KAFKA=10.101.0.1:20407
export ZOOKEEPER=10.101.0.1:20406

yarn # install depednencies
yarn setup # create kafka topics for our widget factory
yarn start # start WidgetCutter and WidgetPainter services
pm2 log # watch the services do their work

# Finally, deliver raw materials to the factory (use another terminal for this)
node src/DeliverBlankWidgets.bs
```

You should see something like this when you deliver your raw materials:

```
$ node src/DeliverBlankWidgets.bs
DeliverBlankWidgets.re connecting to zookeeper at  10.101.0.1:20406
(node:93216) DeprecationWarning: grpc.load: Use the @grpc/proto-loader module with grpc.loadPackageDefinition instead
rx: <Blank Widget condition=adequate>
message send success: { 'blank-widget': { '0': 22 } }
successfully delivered blank widget!
client closed! bye!
```

From the cutter and painter services you should see something like this:

```
0|WidgetCu | rx: <Blank Widget condition=adequate>
0|WidgetCu | cutting widget...
0|WidgetCu | widget cut!
0|WidgetCu | tx: <Cut Widget condition=adequate numTeeth=55>
0|WidgetCu | message send success: { 'cut-widget': { '0': 28 } }
1|WidgetPa | rx: <Cut Widget condition=adequate numTeeth=55>
1|WidgetPa | painting widget...
1|WidgetPa | widget painted!
1|WidgetPa | tx: <Painted Widget condition=adequate numTeeth=55 paintJob=greeN>
1|WidgetPa | message send success: { 'painted-widget': { '0': 39 } }
```
