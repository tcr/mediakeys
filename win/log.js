var path = require('path');
var spawn = require('child_process').spawn;

var proc = spawn(path.resolve('Default/keylistener.exe'), []);
proc.stdout.pipe(process.stdout);
proc.stderr.pipe(process.stderr);
proc.on('exit', function (code) {
	console.error('exited with code', code);
	process.exit(code);
})

// Only fire once to avoid potential overlap (not that this will happen in a 
// well-ordered environment, but you never know).
process.once("SIGTERM", function () {
 
  // Cleanup activities go here...
  // proc.kill();
  proc.disconnect();
 
  // Then shutdown.
  process.exit(0);
});