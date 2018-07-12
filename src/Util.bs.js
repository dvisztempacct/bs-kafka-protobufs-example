// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE
'use strict';

var Grpc = require("./Grpc.bs.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Random = require("bs-platform/lib/js/random.js");
var Js_primitive = require("bs-platform/lib/js/js_primitive.js");
var Caml_exceptions = require("bs-platform/lib/js/caml_exceptions.js");
var Caml_builtin_exceptions = require("bs-platform/lib/js/caml_builtin_exceptions.js");

var EnvironNotFound = Caml_exceptions.create("Util.EnvironNotFound");

function getEnv(k) {
  return Js_primitive.undefined_to_opt(process.env[k]);
}

function getEnvExn(k) {
  var param = process.env[k];
  if (param !== undefined) {
    return param;
  } else {
    throw [
          EnvironNotFound,
          k
        ];
  }
}

function wearWidget(widgetCondition) {
  var match = widgetCondition === /* WidgetConditionDefective */1 || Random.bool(/* () */0);
  if (match) {
    return /* WidgetConditionDefective */1;
  } else {
    return /* WidgetConditionAdequate */0;
  }
}

function widgetConditionToString(param) {
  if (param) {
    if (param[0]) {
      return "defective";
    } else {
      return "adequate";
    }
  } else {
    return "?";
  }
}

function widgetColorToString(param) {
  if (param) {
    switch (param[0]) {
      case 0 : 
          throw [
                Caml_builtin_exceptions.match_failure,
                [
                  "Util.re",
                  41,
                  2
                ]
              ];
      case 1 : 
          return "red";
      case 2 : 
          return "greeN";
      
    }
  } else {
    return "?";
  }
}

function blankWidgetToString(blankWidget) {
  return "<Blank Widget condition=" + (widgetConditionToString(Curry._1(Grpc.Assemblyline[/* BlankWidget */2][/* condition */1], blankWidget)) + ">");
}

function numTeethToString(param) {
  if (param) {
    return String(param[0]);
  } else {
    return "?";
  }
}

function cutWidgetToString(cutWidget) {
  return "<Cut Widget condition=" + (widgetConditionToString(Curry._1(Grpc.Assemblyline[/* CutWidget */3][/* condition */1], cutWidget)) + (" numTeeth=" + (numTeethToString(Js_primitive.undefined_to_opt(cutWidget.numTeeth)) + ">")));
}

function paintedWidgetToString(paintedWidget) {
  return "<Painted Widget condition=" + (widgetConditionToString(Curry._1(Grpc.Assemblyline[/* PaintedWidget */5][/* condition */1], paintedWidget)) + (" numTeeth=" + (numTeethToString(Js_primitive.undefined_to_opt(paintedWidget.numTeeth)) + (" paintJob=" + (widgetColorToString(Curry._1(Grpc.Assemblyline[/* PaintedWidget */5][/* paintJob */2], paintedWidget)) + ">")))));
}

var Assemblyline = 0;

var BlankWidget = 0;

var CutWidget = 0;

var PaintedWidget = 0;

var WidgetCondition = 0;

var WidgetColor = 0;

exports.EnvironNotFound = EnvironNotFound;
exports.getEnv = getEnv;
exports.getEnvExn = getEnvExn;
exports.wearWidget = wearWidget;
exports.Assemblyline = Assemblyline;
exports.BlankWidget = BlankWidget;
exports.CutWidget = CutWidget;
exports.PaintedWidget = PaintedWidget;
exports.WidgetCondition = WidgetCondition;
exports.WidgetColor = WidgetColor;
exports.widgetConditionToString = widgetConditionToString;
exports.widgetColorToString = widgetColorToString;
exports.blankWidgetToString = blankWidgetToString;
exports.numTeethToString = numTeethToString;
exports.cutWidgetToString = cutWidgetToString;
exports.paintedWidgetToString = paintedWidgetToString;
/* Grpc Not a pure module */
