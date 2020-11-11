// Importación de REmatch
const Module = require('../../embuild/bin/rematch_wasm.js');

// Unpack de clases
const {RegEx, RegExOptions} = Module;


let match;
let rgxOptions = new RegExOptions();
rgxOptions.early_output = false;
rgxOptions.line_by_line = false;

let rgx = new RegEx('.*!x{a+}.*', rgxOptions);

let count = 0;


while(match = rgx.findIter("a")) {
    var variables = match.variables();
    for(var i = 0; i < variables.size(); i++) {
        console.log("Variable \"", variables.get(i), "\"");
    }

    count++;
}
console.log(count)