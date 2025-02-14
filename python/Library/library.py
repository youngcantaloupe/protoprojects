import sys


def ParseBook(fileName):
    fullText = {}

    with open(fileName, "r") as inputFile:
        for line in inputFile.readlines():
            rawText, rawNum = line.rsplit("|", 1)
            lineText = rawText.strip()
            lineNum = int(rawNum.strip())
            fullText[lineNum] = lineText

    longestLine = [0, ""]
    for x in fullText:
        if len(fullText[x]) > len(longestLine[1]):
            longestLine = [x, fullText[x]]
        elif len(fullText[x]) == len(longestLine[1]) and x > longestLine[0]:
            longestLine = [x, fullText[x]]

    sortedBook = dict(sorted(fullText.items()))

    totChars = sum(len(lineText) for lineText in sortedBook.values())
    avgLen = totChars / len(sortedBook)

    return sortedBook, longestLine, avgLen


def WriteBook(fileName, book):
    bookName = fileName.split(".")[0] + "_book." + fileName.split(".")[1]
    (bookText, longestLine, avgLen) = book

    with open(bookName, "w") as fileWriter:
        fileWriter.writelines(bookName.split("_")[0] + "\n")
        fileWriter.writelines(f"Longest line ({longestLine[0]}): {longestLine[1]}\n")
        fileWriter.writelines(f"Average length: {avgLen:.0f}\n")
        for value in bookText.values():
            fileWriter.writelines(value + "\n")


def main():
    fileName = sys.argv[1]
    book = ParseBook(fileName)
    WriteBook(fileName, book)


main()
