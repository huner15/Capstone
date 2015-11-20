using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
namespace ProtobufTcasDemo
{

    

    public partial class Form1 : Form
    {
        private int fileNumber = 0;
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            
            Example.TcasReport toSave = new Example.TcasReport();

            try
            {
                toSave.Altitude = Int32.Parse(altitudeTextBox.Text);
                toSave.Bearing = Int32.Parse(bearingTextBox.Text);
                toSave.Id = Int32.Parse(idTextBox.Text);
                toSave.Range = Int32.Parse(rangeTextBox.Text);
            }
            catch(FormatException)
            {

            }
            saveFile(toSave);


        }


        private void saveFile(Example.TcasReport toSave)
        {

            try {
                FileStream outStream = new FileStream(fileNumber + ".tcas", System.IO.FileMode.CreateNew);
                //new System.IO.StreamWriter(fileNumber + ".tcas");

                Example.TcasReport.Serialize(outStream, toSave);
                outStream.Close();
                fileNumber++;
            }
            catch (IOException)
            {
                fileNumber++;
                saveFile(toSave);
            }

        }

        private void button2_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
            Example.TcasReport opened;
                
                
            opened =  Example.TcasReport.Deserialize(openFileDialog1.OpenFile());
            altitudeTextBox.Text = opened.Altitude + "";
            bearingTextBox.Text = opened.Bearing + "";
            idTextBox.Text = opened.Id + "";
            rangeTextBox.Text = opened.Range + "";
        }
    }
}
