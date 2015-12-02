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

    public int maxRange = 20;

    void OnGUI()
    {
        int h = Screen.height;
        int w = Screen.width;
        Console.Write("boom");
        GUI.Label(new Rect(w/1.7f, h/2, 20, 20), "" + (maxRange/4));
        GUI.Label(new Rect(w/1.52f, h/2, 20, 20), "" + (maxRange * 2 / 4));
        GUI.Label(new Rect(w/1.37f, h/2, 20, 20), "" + (maxRange * 3 / 4));
        GUI.Label(new Rect(w/1.26f, h/2, 20, 20), "" + (maxRange));

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
        print("Server Start");
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
                print("2");
                NetworkStream ns = client.GetStream();
                print("3");
                //probably need to do special cross thread call here try without first but with an actual packet of data.
                yield return Ninja.JumpToUnity;
                Msg message = Msg.Deserialize(ns);
                CDTIReport report = new CDTIReport();
                CDTIPlane plane = new CDTIPlane();
                plane.Position = new Vector();
                plane.Position.X = message.Age;
                plane.Position.Y = message.Age;
                report.Planes.Add(plane);
                intake(report);
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

        positon.x = plane.Position.X/maxRange*5;
        positon.y = plane.Position.Y/maxRange*5;
        positon.z = 0;
        //add writing for the elevation later
        return positon;
       // throw new NotImplementedException();
    }

    private Sprite getCorrectSprite(CDTIPlane plane)
    {

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
