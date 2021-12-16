using System;

namespace lab_tests
{
    public class Connection
    {
        private int status = 0;
        private int host = 0;

        public int Run(int new_host)
        {
            int er;
            if (status == 0) {
                status = 1;
                host = new_host;
                er = 0;
            } else { 
                if (host == new_host)
                    er = 1;
                else
                    er = -1;
            }
            return er;
        }

        public int GetStatus()
        {
            return this.status;
        }

        public int Stop()
        {
            if (status > 0)
            {
                status = 0;
                host = 0;
                return -1;
            }
            else
            {
                return -1;
            }
        }
    }
}
