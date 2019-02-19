open Utils;

require("./App.css");

let logo = requireURI("./logo.svg");

let component = ReasonReact.statelessComponent("Greeting");

let make = (~name, _children) => {
  ...component,
  render: _self =>
    <div>
      <img src=logo className="logo" alt="logo" />
      <div> {ReasonReact.string("Welcome to, " ++ name)} </div>
    </div>,
};
