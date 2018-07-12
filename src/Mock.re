module WidgetColor = Grpc.Assemblyline.WidgetColor;

/* This module just contains some make believe asynchronous jobs */
let setTimeout = Util.setTimeout;
/* time it takes to cut a widget */
let howLongDoesItTakeToCutAWidget = 4000;
let howlongDoesItTakeToPaintAWidget = 1000;

let paintWidget = (callback, widgetCondition) =>
  setTimeout(
    () =>
      callback(
        widgetCondition |. Util.wearWidget,
        WidgetColor.(
          Random.bool() ? WidgetColorRed : WidgetColorGreen
        ),
      ),
    howlongDoesItTakeToPaintAWidget,
  ) |> ignore;

let cutWidget = (callback, widgetCondition) => setTimeout(() => callback(
    widgetCondition |. Util.wearWidget,
    Random.int(32) + 32), howLongDoesItTakeToCutAWidget) |> ignore;
