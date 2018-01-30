open Css;

open Helpers;

let styles = {
  "button":
    style([
      display(inlineBlock),
      borderRadius(3 |> px),
      padding2(~v=0.5 |> rem, ~h=0.0 |> rem),
      margin2(~v=0.5 |> rem, ~h=1.0 |> rem),
      width(11.0 |> rem),
      background(transparent),
      color(Theme.white),
      textAlign(center),
      border(2 |> px, solid, Theme.white),
      background(Theme.white),
      color(Theme.palevioletred)
    ]),
  "primary": style([background(Theme.white), color(Theme.palevioletred)])
};

let make = (~onClick, ~className="", ~primary=false, children) => {
  ...ReasonReact.statelessComponent("Button"),
  render: _self =>
    ReasonReact.createDomElement(
      "button",
      ~props={
        "onClick": onClick,
        "className":
          classnames([
            (styles##button, true),
            (styles##primary, primary),
            (className, true)
          ])
      },
      children
    )
};