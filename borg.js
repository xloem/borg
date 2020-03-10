// browserify this-file.js --ignore-missing -o bundle.js
'use strict';
const Blessed = require('blessed');

(async (global) => {

  const window = global.window;
  const opts = window && await new Promise((resolve) => {
    window.onload = () => {

      // const TermJs = require('xterm');
      const TermJs = require('term.js');
      const Terminal = TermJs.Terminal;
      // const Terminal = Blessed.widget.terminal;
      const term = new Terminal({
          cols: 80,
          rows: 24,
          useStyle: true,
          screenKeys: true,
          // rendererType: 'dom', // Don't use canvas in xterm.
      });

      term.open(document.body);
      // term.write('\x1b[31mWelcome to term.js!\x1b[m\r\n');

      // glue to make Blessed work in browserify
      term.columns = term.cols;
      term.isTTY = true;

      term.resize(100,36);
      resolve({ input: term, output: term, tput: false });

    };
  });

  const program = new Blessed.program(opts);

  require('./collective')(program)

})(global || window);
