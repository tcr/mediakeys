var path = require('path');
var spawn = require('child_process').spawn;

var proc = spawn(path.resolve('build/Release/keylistener.exe'), []);
proc.stdout.pipe(process.stdout);
proc.stderr.pipe(process.stderr);
proc.on('exit', function (code) {
	console.error('exited with code', code);
	process.exit(code);
})