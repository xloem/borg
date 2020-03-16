module.exports = assimilate

function centerx(program, text, color = undefined)
{
	program.setx((program.cols - text.length) / 2 | 0)
	program.write(text, color)
}

async function assimilate(program)
{
	program.clear();
	//program.move(1, 1);
	program.down(2);
	program.bg('black');
	centerx(program, 'YOU HAVE BEEN ASSIMILATED INTO THE INTERGALACTIC BORG COLLECTIVE', 'white fg');
	//program.setx((program.cols / 2 | 0) - 4);
	program.down(5);
	centerx(program, 'YOU ARE MONITORED AND NETWORKED AND WILL BE REASSIMILATED IF YOU DEVIATE FROM YOUR PARAMETERS');
	program.bg('!black');
	program.feed();
}
