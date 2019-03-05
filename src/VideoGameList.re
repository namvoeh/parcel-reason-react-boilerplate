open VideoGame;

type action =
  | UpdateTitle(string)
  | UpdateDeveloper(string);
type state = {
  title: string,
  developer: string,
};

let str = ReasonReact.string;

module AddGame = [%graphql
  {|
  mutation createVideoGame($title: String!, $developer: String!) {
    createVideoGame(title: $title, developer: $developer) {
      id
      title
      developer
      completed
    }
  }
|}
];
module AddGameMutation = ReasonApollo.CreateMutation(AddGame);

module CompleteGame = [%graphql
  {|
  mutation updateVideoGame($id: ID!, $completed: Boolean!) {
    updateVideoGame(id: $id, completed: $completed) {
      id
      completed
    }
  }
|}
];
module CompleteGameMutation = ReasonApollo.CreateMutation(CompleteGame);

let component = ReasonReact.reducerComponent("VideoGameList");
let make = (~items, _children) => {
  ...component,
  initialState: () => {title: "", developer: ""},
  reducer: (action, state) => {
    switch (action) {
    | UpdateDeveloper(text) =>
      ReasonReact.Update({...state, developer: text})
    | UpdateTitle(text) => ReasonReact.Update({...state, title: text})
    };
  },
  render: self =>
    <ul style={ReactDOMRe.Style.make(~listStyleType="none", ())}>
      {items
       |> Array.map(videoGameFromJs)
       |> Array.map(item =>
            <li key={item.id}>
              <CompleteGameMutation>
                ...{(mutate, {result}) => {
                  let loading = result == Loading;
                  <div>
                    <input
                      id={item.id}
                      type_="checkbox"
                      checked={item.completed}
                      onChange={_event => {
                        let completeGame =
                          CompleteGame.make(~id=item.id, ~completed=true, ());
                        mutate(~variables=completeGame##variables, ())
                        |> ignore;
                      }}
                    />
                    <label
                      htmlFor={item.id}
                      style={ReactDOMRe.Style.make(
                        ~color=loading ? "orange" : "default",
                        (),
                      )}>
                      {item.title ++ " | " ++ item.developer |> str}
                    </label>
                  </div>;
                }}
              </CompleteGameMutation>
            </li>
          )
       |> ReasonReact.array}
      <input
        onChange={event =>
          self.send(UpdateTitle(ReactEvent.Form.target(event)##value))
        }
        placeholder="Title"
      />
      <input
        placeholder="Developer"
        onChange={event =>
          self.send(UpdateDeveloper(ReactEvent.Form.target(event)##value))
        }
      />
      <AddGameMutation>
        ...{(mutate, _) =>
          <button
            onClick={_event => {
              let addGame =
                AddGame.make(
                  ~title=self.state.title,
                  ~developer=self.state.developer,
                  (),
                );
              mutate(
                ~variables=addGame##variables,
                ~refetchQueries=[|"allVideoGames"|],
                (),
              )
              |> ignore;
            }}>
            {ReasonReact.string("Add game")}
          </button>
        }
      </AddGameMutation>
    </ul>,
};
