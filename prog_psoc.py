#
# This script programs a PSoC 4 device using the PSoC Programmer COM object.
# It is based on the standard programming sequence for PSoC 4 devices, which
# requires programming the flash memory one row at a time.
#
# Requirements:
# 1. PSoC Creator & PSoC Programmer installed.
# 2. Python installed (Python 2.7+ or 3.x).
# 3. pywin32 library installed (run: pip install pywin32).
#

import win32com.client
import sys
# import time


def PSoC4_GetTotalFlashRowsCount(hexImageSize):
    (hr, _, rowSize, _) = pp.PSoC4_GetFlashInfo()
    if (hr < 0):
        print("Error getting flash info")
        return hr
    totalRows = hexImageSize / rowSize
    return (hr, totalRows)


def PSoC4_VerifyFlash(hexImageSize):
    (hr, totalRows) = PSoC4_GetTotalFlashRowsCount(hexImageSize)
    if (hr < 0):
        print("Cannot get FlashRowsCount")
        return hr
    for i in range(0, totalRows):
        (hr, verResult, _) = pp.PSoC4_VerifyRowFromHex(i)
        if (hr < 0):
            return hr
        if (verResult == 0):
            print(f"Verification failed on {i} row")


def program_psoc4(programmer_id, hex_file_path):
    """
    Connects to a PSoC 4 device and programs it with a specified hex file.
    """

    # Use a global variable for the COM object to ensure it's accessible
    # in the 'finally' block for cleanup.
    global pp
    pp = None

    try:
        # --- Step 1: Initialize the PSoC Programmer COM Object ---
        print("Initializing PSoC Programmer...")
        pp = win32com.client.Dispatch(
            "PSoCProgrammerCOM.PSoCProgrammerCOM_Object"
        )

        # --- Step 2: Open the Port and Configure Settings ---
        programmer_path = "E:/Acads/UWM/Programmer"
        print(f"Opening port '{programmer_id}'...")
        (hr, err_str) = pp.OpenPort(programmer_id, programmer_path)
        if hr < 0:
            print(f"Error: Could not open port. {err_str}")
            return

        print("Configuring port settings (SWD, 1.6 MHz, Reset Acquire)...")
        pp.SetPowerVoltage("3.3")
        pp.SetAcquireMode("Reset")
        pp.SetProtocol(8)  # 8 corresponds to SWD protocol [1]
        pp.SetProtocolConnector(1)  # 1 for 10-pin connector
        pp.SetProtocolClock(152)   # 152 corresponds to 1.6 MHz [1]

        # --- Step 3: Load Hex File and Acquire the Device ---
        print(f"Loading hex file: {hex_file_path}")
        (hr, hexImageSize, err_str) = pp.HEX_ReadFile(hex_file_path)
        if hr < 0:
            print(
                f"Error: Could not read hex file. Ensure forward slashes '/'. "
                f"{err_str}"
            )
            return
        # Now, acquire the chip. This allows the programmer to learn the chip's
        # memory layout, which is necessary for the next step.
        print("Acquiring device...")
        (hr, err_str) = pp.DAP_Acquire()
        if hr < 0:
            print(f"Error: Could not acquire device. {err_str}")
            return
        print("Device acquired successfully.")

        # --- Step 4: Get Row Count, Erase, Program, and Verify ---
        (hr, num_rows) = PSoC4_GetTotalFlashRowsCount(hexImageSize)
        num_rows = int(num_rows)
        if hr < 0 or num_rows == 0:
            print(
                f"Error: Could not get row count from hex file. "
                f"Rows found: {num_rows}. {err_str}"
            )
            return

        print(f"Found {num_rows} rows to program.")

        # Erase the chip using the PSoC 4-specific command
        print("Erasing chip...")
        (hr, err_str) = pp.PSoC4_EraseAll()
        if hr < 0:
            print(f"Error: EraseAll failed. {err_str}")
            return
        print("Chip erased.")

        # Program the chip row by row
        print(f"Programming {num_rows} rows of flash...")
        for row in range(num_rows):
            (hr, err_str) = pp.PSoC4_ProgramRowFromHex(row)
            if hr < 0:
                print(f"\nError: Failed to program row {row}. {err_str}")
                return
            # Print progress without a newline
            sys.stdout.write(f"\rProgress: {row + 1}/{num_rows}")
            sys.stdout.flush()
        print("\nProgramming complete.")

        # Verify the chip row by row
        print(f"Verifying {num_rows} rows...")
        for row in range(num_rows):
            (hr, verResult, err_str) = pp.PSoC4_VerifyRowFromHex(row)
            if hr < 0:
                print(f"\nError: Failed to verify row {row}. {err_str}")
                return
            if (verResult == 0):
                print(f"\nVerification failed on row {row}")
                return
            # Print progress without a newline
            sys.stdout.write(f"\rProgress: {row + 1}/{num_rows}")
            sys.stdout.flush()
        print("\nVerification successful.")

        print("\nSUCCESS: Device has been programmed and verified.")

        # pp.PowerOff()
        # time.sleep(0.2)
        # pp.PowerOn()

    except Exception as e:
        print(f"\nAn unexpected error occurred: {e}")
        print("Please ensure PSoC Programmer and pywin32 are installed "
              "correctly.")
        sys.exit(1)

    finally:
        # --- Step 5: Clean Up ---
        # Always ensure the port is closed, even if errors occurred.
        if pp is not None:
            print("Closing port.")
            pp.ClosePort()


# --- Main Execution Block ---
if __name__ == "__main__":
    # --------------------------------------------------------------------
    # USER CONFIGURATION:
    # 1. Set the full path to your.hex file. USE FORWARD SLASHES '/'.
    # 2. Set your programmer's Port ID (from running GetPorts in ppcli.exe).
    # --------------------------------------------------------------------
    HEX_FILE_PATH = (
        "E:/Acads/UWM/Summer 25/PathController/PathController.cydsn/"
        "CortexM0/ARM_GCC_541/Debug/PathController.hex"
    )
    PROGRAMMER_ID = "KitProg (CMSIS-DAP/247912)"

    program_psoc4(PROGRAMMER_ID, HEX_FILE_PATH)
