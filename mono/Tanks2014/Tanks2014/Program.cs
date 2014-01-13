#region Using Statements
using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;

#endregion

namespace Tanks2014
{
	static class Program
	{
		private static TanksGame game;

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main ()
		{
			game = new TanksGame();
			game.Run();
		}
	}
}
