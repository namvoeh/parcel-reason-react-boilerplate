let component = ReasonReact.statelessComponent("RandomDog");
let make = _children => {
  ...component,
  render: _self => <div> {ReasonReact.string("RandomDog API")} </div>,
};
