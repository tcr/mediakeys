{
	"targets": [
		{
			"target_name": "binding",
			"sources": [
				"dummy.cc"
			],
			"dependencies": [
				"win/shell.gyp:keylistener",
				"win/shell.gyp:MMShellHook",
			]
		}
	]
}