var path = require('path');
var spawn = require('child_process').spawn;

function runProgram (cmd) {
	var proc = spawn(cmd, []);
	proc.stdout.pipe(process.stdout);
	proc.stderr.pipe(process.stderr);
	proc.on('exit', function (code) {
		console.error('exited with code', code);
		// process.exit(code);
	})
}

if (process.platform == 'darwin') {
	var cmd = path.join(path.dirname(require('bindings')('binding').path), 'keylistener');
	runProgram(cmd);

} else if (process.platform == 'win32') {
	var cmd = path.join(path.dirname(require('bindings')('binding').path), 'keylistener.exe');
	runProgram(cmd);
} else {
	throw new Error('unsupported platform', process.platform)
}