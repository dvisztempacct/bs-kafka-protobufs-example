// Generated by BUCKLESCRIPT VERSION 4.0.1, PLEASE EDIT WITH CARE
'use strict';

var Util = require("./Util.bs.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Random = require("bs-platform/lib/js/random.js");

function $$setTimeout$1(prim, prim$1) {
  return setTimeout(prim, prim$1);
}

function paintWidget(callback, widgetCondition) {
  setTimeout((function () {
          var match = Random.bool(/* () */0);
          return Curry._2(callback, Util.wearWidget(widgetCondition), match ? /* WidgetColorRed */1 : /* WidgetColorGreen */2);
        }), 1000);
  return /* () */0;
}

function cutWidget(callback, widgetCondition) {
  setTimeout((function () {
          return Curry._2(callback, Util.wearWidget(widgetCondition), Random.$$int(32) + 32 | 0);
        }), 4000);
  return /* () */0;
}

var WidgetColor = 0;

var howLongDoesItTakeToCutAWidget = 4000;

var howlongDoesItTakeToPaintAWidget = 1000;

exports.WidgetColor = WidgetColor;
exports.$$setTimeout = $$setTimeout$1;
exports.howLongDoesItTakeToCutAWidget = howLongDoesItTakeToCutAWidget;
exports.howlongDoesItTakeToPaintAWidget = howlongDoesItTakeToPaintAWidget;
exports.paintWidget = paintWidget;
exports.cutWidget = cutWidget;
/* Util Not a pure module */
