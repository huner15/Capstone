using UnityEngine;
using System.Collections;
using System.Net.Sockets;
using System.Net;
using System;

public class NetworkInput : MonoBehaviour {

    TcpListener server = null;
    NetworkStream stream;
	// Use this for initialization
	void Start () {
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


    }
	
	// Update is called once per frame
	void Update () {

        //try to read in the client info here.

	}
}
