using UnityEngine;
using System.Collections;
using System.Net.Sockets;
using System.Net;
using System;
using Example;
using System.Threading;
using CielaSpike;

public class NetworkInput : MonoBehaviour {

    TcpListener server = null;
    NetworkStream stream;
    Thread mThread;
    private bool isRunning;



    public Sprite airTrafficDirectional, airTrafficNonDirectional, proximateTrafficDirectional, proximateTrafficNonDirectional, resolutionAdvisoryDirectional, trafficAdvisoryDirectional;
    public GameObject aircraftBuilder;
    private System.Collections.Generic.List<GameObject> aircraft = new System.Collections.Generic.List<GameObject>();
    private System.Collections.Generic.List<GameObject> aircraftHidden = new System.Collections.Generic.List<GameObject>();
    public GameObject circle;
    private string message = "";
    public int maxRange = 20;

    private Vector pos = new Vector();
    private GameObject plane;

    static System.IO.StreamWriter writer;

    public static void logger(String str)
    {
        print(str);
        try
        {
            if(writer == null)
            {
                if (!System.IO.File.Exists("log.txt"))
                {
                    System.IO.File.Create("log.txt");
                }

                writer = new System.IO.StreamWriter(System.IO.File.OpenWrite("log.txt"));
             }

             writer.WriteLine(str);
             writer.Flush();
        }
        catch(Exception)
        {
            print("write failled");
        }
    }




    void OnGUI()
    {
        int h = Screen.height;
        int w = Screen.width;
        Console.Write("boom");
        GUI.Label(new Rect(w/1.7f, h/2, 20, 20), "" + (maxRange/4));
        GUI.Label(new Rect(w/1.52f, h/2, 20, 20), "" + (maxRange * 2 / 4));
        GUI.Label(new Rect(w/1.37f, h/2, 20, 20), "" + (maxRange * 3 / 4));
        GUI.Label(new Rect(w/1.26f, h/2, 20, 20), "" + (maxRange));
        GUI.Label(new Rect(w / 2, 0, 100, 20), message);
    }




    // Use this for initialization
    void Start () {
        GameObject addCircles;

        addCircles = Instantiate(circle) as GameObject;
        addCircles.GetComponent<Transform>().localScale =new Vector3(2.6f, 2.6f, 1);
        addCircles.GetComponent<Transform>().position = new Vector3(0f, .14f, 0);
        addCircles = Instantiate(circle) as GameObject;
        addCircles.GetComponent<Transform>().localScale = new Vector3(2f,2f, 1);
        addCircles.GetComponent<Transform>().position = new Vector3(0f, .14f, 0);
        addCircles = Instantiate(circle) as GameObject;
        addCircles.GetComponent<Transform>().localScale = new Vector3(1.4f, 1.4f, 1);
        addCircles.GetComponent<Transform>().position = new Vector3(0f, .14f, 0);
        addCircles = Instantiate(circle) as GameObject;
        addCircles.GetComponent<Transform>().localScale = new Vector3(.8f, .8f, 1);
        addCircles.GetComponent<Transform>().position = new Vector3(0f, .14f, 0);


        plane = Instantiate(aircraftBuilder) as GameObject;
        pos.X = 0;
        pos.Y = -20;
        pos.Z = 0;
        


        isRunning = true;
        this.StartCoroutineAsync(connect());

        //ThreadStart ts = new ThreadStart(connect);
       // mThread = new Thread(ts);
        //mThread.Start();
        print("Thread done...");
        

        /*
        Int32 port = 13000;
        IPAddress localAddr = IPAddress.Parse("127.0.0.1");

        // TcpListener server = new TcpListener(port);
        server = new TcpListener(localAddr, port);
        
        // Start listening for client requests.
        server.Start();

        Console.WriteLine("waiting fr a connection... ");

        TcpClient client = server.AcceptTcpClient();
        Console.WriteLine("Connected");

        stream = client.GetStream();
        */

    }

    public void stopListening()
    {
        isRunning = false;
    }


    IEnumerator connect()
    {
       
        server = new TcpListener(IPAddress.Parse("127.0.0.1"), 13000);
        server.Start();
        logger("server Start");
        while (isRunning)
        {
                // check if new connections are pending, if not, be nice and sleep 100ms
            if (!server.Pending())
            {
                Thread.Sleep(100);
            }
            else
            {
                print("1");
                TcpClient client = server.AcceptTcpClient();
                logger("connection established");
                print("2");
                yield return Ninja.JumpToUnity;
                plane.GetComponent<SpriteRenderer>().sprite = getCorrectSprite(null);
                plane.GetComponent<Transform>().position = figurePositon(null);
                pos.Y += .5f;
                logger("moved");
                /* NetworkStream ns = client.GetStream();
                 ns.ReadByte();
                 ns.ReadByte();
                 ns.ReadByte();
                 ns.ReadByte();

                 //ns.Seek(4, System.IO.SeekOrigin.Begin);
                 print("3");
                 //probably need to do special cross thread call here try without first but with an actual packet of data.
                 yield return Ninja.JumpToUnity;
                 /*
                 try
                 {
                     Msg message = Msg.Deserialize(ns);
                     logger(message.Name);
                     this.message = message.Name;
                     CDTIReport report = new CDTIReport();
                     CDTIPlane plane = new CDTIPlane();
                     plane.Position = new Vector();
                     plane.Position.X = message.Age;
                     plane.Position.Y = message.Age;
                     plane.Position.Z = 0;
                     plane.Id = name;
                     plane.severity = CDTIPlane.Severity.PROXIMATE;
                     plane.Velocity = new Vector();
                     plane.Velocity.X = 0;
                     plane.Velocity.Y = 0;
                     plane.Velocity.Z = 0;
                     AddToScreen(plane);
                 }
                 catch (NotImplementedException)
                 {
                     logger("tried to seek");
                 }
                 */



                //report.Planes.Add(plane);

                // intake(report);
                // intake(CDTIReport.Deserialize(ns));
                yield return Ninja.JumpBack;
                client.Close();
            }
        }

        server.Stop();
        yield return null;
    }
	
	// Update is called once per frame
	void Update () {

        //try to read in the client info here.
        /*if(stream.DataAvailable)
        {
            intake(CDTIReport.Deserialize(stream));
        }*/
	}

    private void  intake(CDTIReport report)
    {
        logger("at intake");

        clearPlanes();

        foreach (CDTIPlane plane in report.Planes)
        {
            AddToScreen(plane);
        }


    }

    private void AddToScreen(CDTIPlane plane)
    {
        GameObject toAdd;
        if (aircraftHidden.Count > 0)
        {
            toAdd = aircraftHidden[0];
            aircraftHidden.Remove(toAdd);
        }
        else
        {
            toAdd = Instantiate(aircraftBuilder) as GameObject;
        }


        toAdd.GetComponent<SpriteRenderer>().sprite = getCorrectSprite(plane);
        toAdd.GetComponent<Transform>().position = figurePositon(plane);




        aircraft.Add(toAdd);
        //throw new NotImplementedException();
    }

    private Vector3 figurePositon(CDTIPlane plane)
    {
        
        Vector3 positon;

        if (plane == null)
        {
            positon.x = pos.X / maxRange * 5;
            positon.y = pos.Y / maxRange * 5;
            positon.z = 0;
            return positon;
        }


        positon.x = plane.Position.X/maxRange*5;
        positon.y = plane.Position.Y/maxRange*5;
        positon.z = 0;
        //add writing for the elevation later
        return positon;
       // throw new NotImplementedException();
    }

    private Sprite getCorrectSprite(CDTIPlane plane)
    {
        if(plane == null)
        {
            return airTrafficDirectional;
        }

        Vector zeroVector = new Vector();
        zeroVector.X = 0;
        zeroVector.Y = 0;
        zeroVector.Z = 0;
        switch (plane.severity) {
            case (CDTIPlane.Severity.PROXIMATE):
                if (plane.Velocity == zeroVector)
                {
                    return proximateTrafficNonDirectional;
                }
                else
                    return proximateTrafficDirectional;
            case (CDTIPlane.Severity.TRAFFIC):
                return trafficAdvisoryDirectional;
            case (CDTIPlane.Severity.RESOLUTION):
                return resolutionAdvisoryDirectional;

            default:
                if (plane.Velocity == zeroVector)
                {
                    return airTrafficNonDirectional;
                }
                else
                    return airTrafficDirectional;
                
        }
            
                

        throw new NotImplementedException();
    }

    private void clearPlanes()
    {
        foreach(GameObject plane in aircraft)
        {
            plane.GetComponent<SpriteRenderer>().sprite = null;
            aircraftHidden.Add(plane);
           // Destroy(plane);
            
        }
        aircraft.Clear();


       // throw new NotImplementedException();
    }

    void OnApplicationQuit()
    {
        // stop listening thread
        stopListening();
        // wait fpr listening thread to terminate (max. 500ms)
      //  mThread.Join(500);
    }
}
