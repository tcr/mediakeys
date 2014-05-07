{
	"targets": [
		{
			"target_name": "binding",
			"dependencies": [
				"keylistener"
			]
		},
		{
			"target_name": "keylistener",
			"type": "shared_library",
			"sources": [
				"MMShellHook.cpp"
			]
		}
	]
}
