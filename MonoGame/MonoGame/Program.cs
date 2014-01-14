#region Using Statements
using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Tanks2014;
#endregion

namespace MonoGame
{
	static class Program
	{
		private static Game game;

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main ()
		{
			game = new TanksGame ();
			game.Run ();
		}
	}
}
