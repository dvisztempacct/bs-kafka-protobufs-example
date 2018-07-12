# bs-kafka example

We're in the business of making widgets, and this is our microservices solution!

To use, first clone this repo, then:

```
# Export something like this:
export KAFKA=10.101.0.1:20407
export ZOOKEEPER=10.101.0.1:20406

# If you have VPN set you can do this probably:
export KAFKA=10.101.0.1:$((20007 + $VPN))
export ZOOKEEPER=10.101.0.1:$((20006 + $VPN))

yarn # install depednencies
yarn setup # create kafka topics for our widget factory
yarn start # start WidgetCutter and WidgetPainter services
pm2 log # watch the services do their work

# Finally, deliver raw materials to the factory (use another terminal for this)
node src/DeliverBlankWidgets.bs
```
