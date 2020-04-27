const path = require("path");
const HtmlWebpackPlugin = require('html-webpack-plugin');

module.exports = {
  entry: "./examples/index.bs.js",
  mode: "development",
  plugins: [
    new HtmlWebpackPlugin({
      title: 'Reason Fetch Examples',
    }),
  ],
  devServer: {
    contentBase: path.join(__dirname, "public"),
    port: 9000,
  }
};
