/*
 * Released under the "Do as you like" License
 * Erik Johnson
 * - erik@erikjohnson.ca
 * - @erikjohnzon
 *
 */
var async = require('async'),
    util = require('util'),
    exec = require('child_process').exec,
    child;

module.exports = {
    pkg : function () {
        child = exec("blackberry-nativepackager @options", function (error, stdout, stderr) {
            if(error) {
                util.print(stderr);
                console.log(error);
            } else {
                console.log("Packaging application complete");
            }
        });
    },

    deploy: function () {
        var args = Array.prototype.slice.call(arguments)[0],
            ip = args[0] || "169.254.0.1",
            barPath = args[1] || "build/output/hnapp.bar",
            password = args[2] || "qaqa";

        child = exec("blackberry-deploy -installApp " + ip + " " + barPath + " -password " + password , function (error, stdout, stderr) {
            if(error) {
                util.print(stderr);
                console.log(error);
            } else {
                console.log(stdout);
                console.log("Application deployed");
            }
        });
    }
};
