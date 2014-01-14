using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;

namespace Tanks2014
{
    /// <summary>
    /// This is the main type for your game
    /// </summary>
    public class TanksGame : Game
    {
        private static int FPS = 30;

        private double lFps;
        private double dFps;

        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        Texture2D sprite;
        Spriter drawer;
        Mode currentMode;

        public void setMode(Mode newMode)
        {
            currentMode = newMode;
        }

        public TanksGame()
        {
            graphics = new GraphicsDeviceManager(this);
        	graphics.PreferredBackBufferWidth = 640;
        	graphics.PreferredBackBufferHeight = 640;
        	graphics.IsFullScreen = false;

            Content.RootDirectory = "Content";
        }

        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// This is where it can query for any required services and load any non-graphic
        /// related content.  Calling base.Initialize will enumerate through any components
        /// and initialize them as well.
        /// </summary>
        protected override void Initialize()
        {
            //TargetElapsedTime = TimeSpan.FromMilliseconds(1000.0 / FPS);
            currentMode = new TestMode(this);
            base.Initialize();
        }

        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        {
            spriteBatch = new SpriteBatch(GraphicsDevice);
            sprite = Content.Load<Texture2D>("sprite");
            drawer = new Spriter(this, spriteBatch, sprite);

            // TODO: use this.Content to load your game content here
        }

        /// <summary>
        /// UnloadContent will be called once per game and is the place to unload
        /// all content.
        /// </summary>
        protected override void UnloadContent()
        {
            // TODO: Unload any non ContentManager content here
        }

        /// <summary>
        /// Allows the game to run logic such as updating the world,
        /// checking for collisions, gathering input, and playing audio.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Update(GameTime gameTime)
        {
            lFps = 1.0 / gameTime.ElapsedGameTime.TotalSeconds;
            currentMode.update(gameTime);
            base.Update(gameTime);
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.Black);

            spriteBatch.Begin();
            currentMode.draw(gameTime, drawer);
            spriteBatch.End();

			dFps = 1.0 / gameTime.ElapsedGameTime.TotalSeconds;
			base.Window.Title = "Tanks 2014 LFPS:" + lFps + " DFPS:" + dFps;
			base.Window.Title += " " + base.GraphicsDevice.Viewport.Width + "/" + base.GraphicsDevice.Viewport.Width;
            base.Draw(gameTime);
        }
    }
}
