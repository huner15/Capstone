using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using Example;

namespace EasyDemoModeGo
{
    class Program
    {

        static TcpClient client = new TcpClient();
        static NetworkStream stream;
        static List<CDTIPlane> planes;
        static int steps;
        static void Main(string[] args)
        {
            if (int.TryParse(args[0], out steps))
            {
                planes = new List<CDTIPlane>();
                buildPlanes();
                connect();
                stepAndSend();
            }
            else
            {
                Console.Write("please indicate the number of steps");
            }

        }

        private static void connect()
        {
            try
            {
                client.Connect("localhost", 13000);
            }
            catch (SocketException)
            {

            }
            try
            {

                stream = client.GetStream();
            }
            catch (Exception)
            {
                return;
            }
        }

        private static void stepAndSend()
        {
            while (steps > 0 || steps == -5)
            {
                figureSeverity();
                send();
                step();
                if(steps > 0)
                    steps--;
                System.Threading.Thread.Sleep(1000);
            }
        }

        private static void step()
        {
            foreach (CDTIPlane plane in planes)
            {
                plane.Position.X += plane.Velocity.X;
                plane.Position.Y += plane.Velocity.Y;
                plane.Position.Z += plane.Velocity.Z;
            }
        }

        private static void send()
        {
            Example.CDTIReport report = new Example.CDTIReport();
            Example.CDTIPlane ownship = new Example.CDTIPlane();
            ownship.Id = "ownship";
            ownship.Position = new Example.Vector(0, 0, 0);
            ownship.Velocity = new Example.Vector(0, 0, 0);
            ownship.severity = (Example.CDTIPlane.Severity)0;
            report.Ownship = ownship;
            report.Timestamp = 5;
            report.AdvisoryLevel = (Example.CDTIReport.Severity)0;
            report.AdvisoryMessage = "send success";
            report.Planes = planes;
            byte junkByte = 200;
            stream.WriteByte(junkByte);
            Example.CDTIReport.Serialize(stream, report);
        }

        private static void figureSeverity()
        {
           // throw new NotImplementedException();
        }

        private static void buildPlanes()
        {
            planes.Add(buildPlanes(3.0, 4.0, 200.0, .1, .05, 0, "demo 1"));
            planes.Add(buildPlanes(20.0, 3.0, 1000.0, -.2, 0, -1, "demo 2"));
            planes.Add(buildPlanes(10.0, 10.0, 0, -.2, -.1, -5, "demo 3"));
            planes.Add(buildPlanes(-50.0, -25.0, 0, .1, .02, 0, "demo 4"));
        }

        private static CDTIPlane buildPlanes(double px, double py, double pz, double vx, double vy, double vz, string id)
        {
            CDTIPlane toReturn = new CDTIPlane();
            Vector v = new Vector();
            Vector p = new Vector();
            p.X = (float)px;
            p.Y = (float)py;
            p.Z = (float)pz;
            v.X = (float)vx;
            v.Y = (float)vy;
            v.Z = (float)vz;
            toReturn.Position = p;
            toReturn.Velocity = v;
            toReturn.Id = id;
            return toReturn;
        }
    }
}
