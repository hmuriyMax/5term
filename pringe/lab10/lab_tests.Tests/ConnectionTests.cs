using System;
using Xunit;

namespace lab_tests.Tests
{
    public class ConnectionTests
    {
        [Fact]
        public void Run_1230()
        {
            int host = 1230;
            int expErr = 0;

            Connection c = new Connection();
            int got = c.Run(host);

            Assert.Equal(expErr, got);
        }

        [Fact]
        public void Run_error()
        {
            int host = 1230;
            int expErr = 1;

            Connection c = new Connection();
            c.Run(host);
            int got = c.Run(host);

            Assert.Equal(expErr, got);
        }

        [Fact]
        public void Stop_state()
        {
            int host = 1230;
            int expErr = 0;

            Connection c = new Connection();
            c.Run(host);
            int got = c.Stop();

            Assert.Equal(expErr, got);
        }

        [Fact]
        public void Stop_error()
        {
            int host = 1230;
            int expErr = -1;

            Connection c = new Connection();
            int got = c.Stop();

            Assert.Equal(expErr, got);
        }

        [Fact]
        public void GetStatus_1230()
        {
            int host = 1230;
            int expErr = 1;

            Connection c = new Connection();
            c.Run(host);
            int got = c.GetStatus();

            Assert.Equal(expErr, got);
        }
    }
}
