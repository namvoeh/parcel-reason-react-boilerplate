module VideoGames = [%graphql
  {|
  query allVideoGames {
    allVideoGames {
      id
      title
      developer
      completed
    }
  }
|}
];

module VideoGamesQuery = ReasonApollo.CreateQuery(VideoGames);

let str = ReasonReact.string;

let component = ReasonReact.statelessComponent("GraphQLSample");

let make = _children => {
  ...component,
  render: _self => {
    let videoGamesQuery = VideoGames.make();
    <div>
      <h1> {"ReasonML + ReasonReact + GraphQL" |> str} </h1>
      <VideoGamesQuery variables=videoGamesQuery##variables>
        ...{({result}) =>
          switch (result) {
          | Loading => <div> {"Loading video games!" |> str} </div>
          | Error(error) => <div> {error##message |> str} </div>
          | Data(data) => <VideoGameList items=data##allVideoGames />
          }
        }
      </VideoGamesQuery>
    </div>;
  },
};
