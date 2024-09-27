const express = require('express');
const app = express();
const port = 8080;

app.get('/test', (req, res) => {
  res.json({ message: 'Hello, this is a test response' });
});

app.listen(port, () => {
  console.log(`Server is running on http://localhost:${port}/test`);
});
