var DBus = require('../');

var dbus = new DBus();

var bus = dbus.getBus('session');

bus.getInterface('org.gnome.SettingsDaemon', '/org/gnome/SettingsDaemon/MediaKeys', 'org.gnome.SettingsDaemon.MediaKeys', function(err, iface) {

iface.addMethod('MediaPlayerKeyPressed', { in: DBus.Define(Array, 'list') }, function(list, callback) {
	console.log(list);
	callback(true);
});

});