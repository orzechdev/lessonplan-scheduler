import Vue from 'vue';
import Vuetify from 'vuetify/lib';

import colors from 'vuetify/lib/util/colors';

Vue.use(Vuetify);

export default new Vuetify({
  icons: {
    iconfont: 'mdi'
  },
  theme: {
    themes: {
      light: {
        primary: colors.blue.darken1,
        secondary: colors.blue.lighten1,
        accent: colors.blue.darken2,
        error: colors.red.darken2
      }
    }
  }
});
