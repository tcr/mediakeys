var path = require('path');
var spawn = require('child_process').spawn;

var cmd = path.join(path.dirname(require('bindings')('binding').path), 'keylistener.exe');

var proc = spawn(cmd, []);
proc.stdout.pipe(process.stdout);
proc.stderr.pipe(process.stderr);
proc.on('exit', function (code) {
	console.error('exited with code', code);
	process.exit(code);
})