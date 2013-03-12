/*
 * Released under the "Do as you like" License
 * Erik Johnson
 * - erik@erikjohnson.ca
 * - @erikjohnzon
 *
 */
var async = require('async'),
    sys = require('sys'),
    exec = require('child_process').exec,
    child;

module.exports = {
    package : function () {
        child = exec("blackberry-nativepackager @options", function (error, stdout, stderr) {
            if(error) {
                sys.print(stderr);
                console.log(error);
            } else {
                console.log("Packaging application complete");
            }
        }
    }
});
