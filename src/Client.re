let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

let httpLink =
  ApolloLinks.createHttpLink(
    ~uri="https://api.graph.cool/simple/v1/cjsuekufj1r0r0151chg63jsi",
    (),
  );

let instance =
  ReasonApollo.createApolloClient(~link=httpLink, ~cache=inMemoryCache, ());
