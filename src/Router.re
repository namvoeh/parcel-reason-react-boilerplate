module Create = (Config: Route.Config) => {
  type route = Config.route;
  type action =
    | UpdateRoute(route);

  type state = {route};
  type renderProps = {
    updateRoute: route => unit,
    currentRoute: route,
  };

  let component = ReasonReact.reducerComponent("Router");

  let make = (~render, _children) => {
    ...component,
    initialState: () => {
      route: ReasonReact.Router.dangerouslyGetInitialUrl() |> Config.toRoute,
    },
    didMount: ({send, onUnmount}) => {
      let watcherID =
        ReasonReact.Router.watchUrl(url =>
          UpdateRoute(Config.toRoute(url)) |> send
        );
      onUnmount(() => ReasonReact.Router.unwatchUrl(watcherID));
    },
    reducer: (action, _state) => {
      switch (action) {
      | UpdateRoute(route) => ReasonReact.Update({route: route})
      };
    },
    render: self => {
      render({
        updateRoute: route => self.send(UpdateRoute(route)),
        currentRoute: self.state.route,
      });
    },
  };
};
