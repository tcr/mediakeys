var DBus = require('dbus');

var dbus = new DBus();

var bus = dbus.getBus('session');

bus.getInterface('org.gnome.SettingsDaemon', '/org/gnome/SettingsDaemon/MediaKeys', 'org.gnome.SettingsDaemon.MediaKeys', function(err, iface) {

	iface.on('MediaPlayerKeyPressed', function(keys) {
		console.log(keys);
	});

});