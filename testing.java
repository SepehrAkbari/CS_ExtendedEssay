import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ExecutionTimeMeasurement {
    public static void main(String[] args) throws IOException {
        // Compile and run the first C program
        String cProgram1 = "splay_tree.c";  // Replace with your C program filename
        long startTime1 = System.nanoTime();
        executeCProgram(cProgram1);
        long endTime1 = System.nanoTime();
        long executionTime1 = endTime1 - startTime1;

        // Compile and run the second C program
        String cProgram2 = "balanced_avl_tree.c";  // Replace with your C program filename
        long startTime2 = System.nanoTime();
        executeCProgram(cProgram2);
        long endTime2 = System.nanoTime();
        long executionTime2 = endTime2 - startTime2;

        System.out.println("Execution Time for Program 1: " + executionTime1 + " nanoseconds");
        System.out.println("Execution Time for Program 2: " + executionTime2 + " nanoseconds");
    }

    private static void executeCProgram(String programFilename) throws IOException {
        // Compile the C program
        Process compileProcess = Runtime.getRuntime().exec("gcc -o " + programFilename.replace(".c", "") + " " + programFilename);
        waitForProcess(compileProcess);

        // Run the compiled program
        Process runProcess = Runtime.getRuntime().exec("./" + programFilename.replace(".c", ""));
        waitForProcess(runProcess);
    }

    private static void waitForProcess(Process process) throws IOException {
        try {
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Error: Process exited with code " + exitCode);
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}
