using System;

namespace Tanks2014
{
#if WINDOWS || XBOX
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        static void Main(string[] args)
        {
            using (TanksGame game = new TanksGame())
            {
                game.Run();
            }
        }
    }
#endif
}

