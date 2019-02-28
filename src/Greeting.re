open Utils;

require("./App.css");

module Styles = {
  open Css;

  let header =
    style([fontWeight(bold), fontSize(rem(1.5))]);
};

let logo = requireURI("./logo.svg");

let component = ReasonReact.statelessComponent("Greeting");

let make = (~name, _children) => {
  ...component,
  render: _self =>
    <div>
      <img src=logo className="logo" alt="logo" />
      <div className=Styles.header>
        {ReasonReact.string("Welcome to, " ++ name)}
      </div>
    </div>,
};
