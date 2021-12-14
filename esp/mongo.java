ConnectionString connectionString = new ConnectionString("mongodb+srv://penda_18:Yayefall99@cluster1.dqbti.mongodb.net/test?retryWrites=true&w=majority");
MongoClientSettings settings = MongoClientSettings.builder()
        .applyConnectionString(connectionString)
        .build();
MongoClient mongoClient = MongoClients.create(settings);
MongoDatabase database = mongoClient.getDatabase("test");
