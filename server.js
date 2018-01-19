const axios = require('axios');
const express = require('express');
const bodyParser = require('body-parser');

const app = express();
app.use(bodyParser());

const forwardJson = (res, path) => {
  console.log(path);
  axios
    .get(`https://instagram.com${path}`)
    .then(({ data }) => res.json(data))
    .catch(err => res.status(500).send(err));
};

app.get('/api/users/:username', (req, res) => {
  const { username } = req.params;
  forwardJson(res, `/${username}/?__a=1`);
});

app.get('/api/users/:username/:picture', (req, res) => {
  const { username, picture } = req.params;
  forwardJson(res, `/p/${picture}/?taken-by=${username}&__a=1`);
});

app.listen(4000, () => console.log('Server at: localhost:4000'));
