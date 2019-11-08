module.exports = {
  "transpileDependencies": [
    "vuetify"
  ],
  chainWebpack: config => {
    // remove vue-cli-service's progress output
    config.plugins.delete('progress')
  },
  devServer: {
    watchOptions: {
      poll: true
    }
  }
}