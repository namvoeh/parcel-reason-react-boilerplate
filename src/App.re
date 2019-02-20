type state = {currentRoute: Route.t};

type action =
  | Navigate(Route.t);

let component = ReasonReact.reducerComponent("app");

let make = _children => {
  ...component,
  initialState: () => {
    currentRoute:
      ReasonReact.Router.dangerouslyGetInitialUrl() |> Route.urlToRoute,
  },
  reducer: (action, _state) =>
    switch (action) {
    | Navigate(route) => ReasonReact.Update({currentRoute: route})
    },
  didMount: ({send, onUnmount}) => {
    let watcherID =
      ReasonReact.Router.watchUrl(url =>
        Route.urlToRoute(url)->Navigate->send
      );
    onUnmount(() => ReasonReact.Router.unwatchUrl(watcherID));
  },
  render: ({state}) => {
    switch (state.currentRoute) {
    | Home =>
      <div>
        <Greeting name="Parcel Reason React Template" />
        <a href={Route.routeToUrl(RandomDog)}>
          {ReasonReact.string("Dog")}
        </a>
      </div>
    | RandomDog => <div> {ReasonReact.string("RandomDog")} </div>
    | NotFound => <div> {ReasonReact.string("Not Found")} </div>
    };
  },
};
