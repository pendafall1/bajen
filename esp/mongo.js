const { MongoClient } = require('mongodb');
const uri = "mongodb+srv://penda_18:Yayefall99@cluster1.dqbti.mongodb.net/test?retryWrites=true&w=majority";
const client = new MongoClient(uri, { useNewUrlParser: true, useUnifiedTopology: true });
client.connect(err => {
  const collection = client.db("test").collection("devices");
  // perform actions on the collection object
  client.close();
});
FROM node:alpine
COPY . /app
WORKDIR /app
CMD node app.js
