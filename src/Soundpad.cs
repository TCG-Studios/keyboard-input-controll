using System.IO;
using System.Text;
using System;
using System.Threading;

namespace soundpad
{
	enum PlayStatus
	{
		STOPPED,
		PLAYING,
		PAUSED,
		SEEKING
	}

	class SoundpadRemoteControl
	{
		public const string CLIENT_VERSION = "1.1.1";
		private const string PIPE_NAME = @"\\.\pipe\sp_remote_control";
		private const int BUFFER_SIZE = 1024;

		private readonly bool PRINT_ERRORS = true;
		private long lastRequestTimestamp = DateTime.Now.Ticks;
		private FileStream pipe = null;

		private readonly Encoding CHARSET_UTF8 = Encoding.UTF8;

		public void Init()
		{
			if (pipe == null)
			{
				pipe = new FileStream(PIPE_NAME, FileMode.OpenOrCreate, FileAccess.ReadWrite);
			}
		}

		public void Uninit()
		{
			if (pipe != null)
			{
				try
				{
					//pipe.Close();
				}
				catch (IOException)
				{
				}
				finally
				{
					pipe = null;
				}
			}
		}

		private string SendRequest(string request)
		{
			Init();

			if (DateTime.Now.Ticks == lastRequestTimestamp)
			{
				// doing too many requests at the same time can break the pipe
				try
				{
					Thread.Sleep(2000);
				}
				catch (Exception)
				{
				}
			}

			byte[] requestBytes = CHARSET_UTF8.GetBytes(request);
			pipe.Write(requestBytes, 0, requestBytes.Length);

			// data size in pipe is first acquirable after reading one byte
			byte[] firstByte = new byte[1];
			pipe.Read(firstByte, 0, 1);
			byte[] responseBytes = new byte[pipe.Length + 1];
			responseBytes[0] = firstByte[0];
			pipe.Read(responseBytes, 1, responseBytes.Length - 1);

			lastRequestTimestamp = DateTime.Now.Ticks;

			return CHARSET_UTF8.GetString(responseBytes);
		}

		private string SendRequestNoException(string request)
		{
			try
			{
				return SendRequest(request);
			}
			catch (IOException)
			{
				Uninit();
			}
			return "";
		}

		private void PrintOfflineError()
		{
			if (PRINT_ERRORS)
			{
				Console.Error.WriteLine("Remote control is offline.");
			}
		}

		private void PrintNumericError(string response)
		{
			if (PRINT_ERRORS)
			{
				Console.Error.WriteLine("Expected numeric response, but received: " + response);
			}
		}

		private void PrintError(string response)
		{
			if (PRINT_ERRORS)
			{
				Console.Error.WriteLine("Failed: " + response);
			}
		}

		private bool IsSuccess(string response)
		{
			return response.StartsWith("R-200");
		}

		private bool IsSuccessPrintResponse(string response)
		{
			if (!response.Equals("R-200"))
			{
				PrintError(response);
				return false;
			}
			return true;
		}
		
		private long HandleNumericLongGetRequest(string request)
		{
			string response = SendRequestNoException(request);
			if (response.StartsWith("R"))
			{
				PrintError(response);
			}
			else if (response.Equals(""))
			{
				PrintOfflineError();
			}
			else
			{
				try
				{
					return long.Parse(response);
				}
				catch (FormatException)
				{
					PrintNumericError(response);
				}
			}
			return -1;
		}
		
		private string HandleStringGetRequest(string request)
		{
			String response = SendRequestNoException(request);
			if (response.StartsWith("R"))
			{
				PrintError(response);
			}
			else if (response.Length == 0)
			{
				PrintOfflineError();
			}
			return response;
		}
		
		private string handleEmptyGetRequest(string request)
		{
			string response = SendRequestNoException(request);
			if (response.Length == 0)
			{
				PrintOfflineError();
			}
			return response;
		}
		
	}
}
