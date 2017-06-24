import java.io.File

// Define new data types
data class Color(val red: Int, val green: Int, val blue: Int) {

    override fun toString(): String {
        return "$red $green $blue"
    }
}

data class Rectangle(val x: Int, val y: Int, val dx: Int, val dy: Int, val color: Color)

fun main(args: Array<String>) {

    //--------------------------------------- READ INPUT DATA
    val inputLines = File("U2.txt").readLines()
    val n = inputLines[0].toInt()
    val rectangles = inputLines.takeLast(n).map {
        // convert all other lines to rectangles
        val ints = it.split(" ").map { it.toInt() } // convert to list of Ints
        val (x, y, dx, dy) = ints.take(4) // first 4 numbers define rectangle
        val (red, green, blue) = ints.takeLast(3) // last 3 numbers define color
        Rectangle(x, y, dx, dy, Color(red, green, blue)) // create new Rectangle and add it to rectangles list
    }
    val rightColumn = rectangles.map { it.x + it.dx }.max()
    val bottomRow = rectangles.map { it.y + it.dy }.max()

    //--------------------------------------- INITIALIZE DRAWING
    val drawing = ArrayList<Color>()
    for (i in 1..100 * 100) {
        drawing.add(Color(255, 255, 255)) // make all picture white
    }

    //--------------------------------------- DRAW RECTANGLES
    rectangles.forEach { draw(it, drawing) }

    //--------------------------------------- WRITE RESULT
    val outputFile = File("U2rez.txt")
    outputFile.delete() // clear file

    outputFile.appendText("$bottomRow $rightColumn\n")
    for (row in 0..bottomRow!! - 1) {
        for (column in 0..rightColumn!! - 1) {
            val color = drawing[100 * row + column];
            outputFile.appendText("$color\n")
        }
    }
}

fun draw(rect: Rectangle, drawing: ArrayList<Color>) {
    println("$rect $drawing")
    for (row in rect.y..rect.y + rect.dy - 1) {
        for (column in rect.x..rect.x + rect.dx - 1) {
            drawing[100 * row + column] = rect.color
        }
    }
}
