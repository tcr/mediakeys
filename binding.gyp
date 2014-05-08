{
	"targets": [
		{
			"target_name": "binding",
			"sources": [
				"dummy.cc"
			],
			"conditions": [
				['OS=="win"', {
					"dependencies": [
						"win/shell.gyp:keylistener",
						"win/shell.gyp:MMShellHook",
					]
				}],
				['OS=="mac"', {
					"dependencies": [
						"osx/osx.gyp:keylistener",
					]
				}],
				['OS=="linux", {
					"dependencies": [
						"dbus/binding.gyp:dbus"
					]
				}]
			]
		}
	]
}