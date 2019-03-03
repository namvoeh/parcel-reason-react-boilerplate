open Route;

module Home = {
  let component = ReasonReact.statelessComponent("Home");
  let make = _children => {
    ...component,
    render: _self =>
      <div>
        <Greeting name="Parcel Reason React Template" />
        <Link route=RandomDog> {ReasonReact.string("Dog")} </Link>
      </div>,
  };
};

module AppRouter = Router.Create(Route.Config);

let component = ReasonReact.statelessComponent("app");

let make = _children => {
  ...component,
  render: _self =>
    <AppRouter
      render={({currentRoute}) =>
        switch (currentRoute) {
        | Home => <Home />
        | RandomDog => <RandomDog />
        | NotFound => <div> {ReasonReact.string("Not Found")} </div>
        }
      }
    />,
};
