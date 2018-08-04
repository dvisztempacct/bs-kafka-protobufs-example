/* Access to environment variables */
exception EnvironNotFound(string);

[@bs.val] [@bs.scope "process"] external env : Js.Dict.t(string) = "";

let getEnv = k => k |> Js.Dict.get(env);

let getEnvExn = k =>
  k
  |> Js.Dict.get(env)
  |. (
    fun
    | Some(x) => x
    | None => raise(k |. EnvironNotFound)
  );

/* setTimeout used for asynchronous delay (for mocking async calls) */
type timeout;
[@bs.val] external setTimeout : (unit => unit, int) => timeout = "";

let wearWidget = widgetCondition =>
  Grpc.Assemblyline.WidgetCondition.(
    widgetCondition == WidgetConditionDefective || Random.bool() ?
      WidgetConditionDefective : WidgetConditionAdequate
  );

module Assemblyline = Grpc.Assemblyline;
module BlankWidget = Assemblyline.BlankWidget;
module CutWidget = Assemblyline.CutWidget;
module PaintedWidget = Assemblyline.PaintedWidget;
module WidgetCondition = Assemblyline.WidgetCondition;
module WidgetColor = Assemblyline.WidgetColor;

let widgetConditionToString =
  fun
  | Some(WidgetCondition.WidgetConditionAdequate) => "adequate"
  | Some(WidgetCondition.WidgetConditionDefective) => "defective"
  | None => "?";

let widgetColorToString =
  fun
  | Some(WidgetColor.WidgetColorGreen) => "greeN"
  | Some(WidgetColor.WidgetColorRed) => "red"
  | None => "?";

let blankWidgetToString = blankWidget =>
  "<Blank Widget condition="
  ++ (blankWidget |. BlankWidget.conditionGet |. widgetConditionToString)
  ++ ">";

let numTeethToString =
  fun
  | Some(n) => n |. string_of_int
  | None => "?";

let cutWidgetToString = cutWidget =>
  "<Cut Widget condition="
  ++ (cutWidget |. CutWidget.conditionGet |. widgetConditionToString)
  ++ " numTeeth="
  ++ (cutWidget |. CutWidget.numTeethGet |. numTeethToString)
  ++ ">";

let paintedWidgetToString = paintedWidget =>
  "<Painted Widget condition="
  ++ (paintedWidget |. PaintedWidget.conditionGet |. widgetConditionToString)
  ++ " numTeeth="
  ++ (paintedWidget |. PaintedWidget.numTeethGet |. numTeethToString)
  ++ " paintJob="
  ++ (paintedWidget |. PaintedWidget.paintJobGet |. widgetColorToString)
  ++ ">";
