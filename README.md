# bs-kafka example

We're in the business of making widgets, and this is our microservices solution!

To use, first clone this repo, then:

```
# Export something like this:
export KAFKA=10.101.0.1:20407
export ZOOKEEPER=10.101.0.1:20406

# Make sure [kafka-cli](https://github.com/shafreeck/kafka-cli) is on your PATH:
PATH="$HOME/go/bin:$PATH"

yarn # install depednencies
yarn build # build
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

## Troubleshooting

If you're getting offsetOutOfRange error, you may have to manually reset your
consumer group's offsets. Install the main Kafka distribution with `brew
install kafka` and then launch `zkCli` and do something like this:

```
donviszneki@Lilys-MBP ~/sysalive-microservice/node_modules/kafka-node$ zkCli -server $ZOOKEEPER
Connecting to 10.101.0.1:20406
Welcome to ZooKeeper!
JLine support is enabled
[zk: 10.101.0.1:20406(CONNECTING) 0]
WATCHER::

WatchedEvent state:SyncConnected type:None path:null
ls /
[log_dir_event_notification, isr_change_notification, zookeeper, admin, consumers, cluster, config, latest_producer_id_block, controller, brokers, controller_epoch]
[zk: 10.101.0.1:20406(CONNECTED) 1] ls /consumers/
Command failed: java.lang.IllegalArgumentException: Path must not end with / character
[zk: 10.101.0.1:20406(CONNECTED) 2] ls /consumers
[kafka-node-group]
[zk: 10.101.0.1:20406(CONNECTED) 3] ls /consumers/kafka-node-group
[offset]
[zk: 10.101.0.1:20406(CONNECTED) 4] l
```
