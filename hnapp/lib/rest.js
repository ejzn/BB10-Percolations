/*
 *
 * Simple wrapper to make my life easy in calling APIs
 * I've written XMLHttpRequest too many times :)
 */

var restjs = {
    open: function (method, url, callback) {
        var request = new XMLHttpRequest();
        request.onreadystatechanged = function (e) {
            if (req.readyState != 4) {
                return;
            }
            if (typeof callback === 'function') {
                callback(this.responseText);
            }
        };
        request.open(method, url);
        request.send(null);
    }
};
